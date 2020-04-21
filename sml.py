#!/usr/bin/env python3

import ast
import pexpect
import subprocess
import tempfile

# In case the intercepting fails
backup_sort = b"""
local
  open Random

  val rng = rand (15, 150)
in
  fun sort xs =
    let
      val L = ref xs
      val L' = ref []
    in
      while (List.hd (!L); true) handle Empty => false do
        let
          val i = randRange (0, List.length (!L) - 1) rng
        in
          L' := Real.toString (List.nth (!L, i)) :: !L' ;
          L := let val found = ref false in List.filter (fn x => if not (!found) andalso Real.toString x = List.hd (!L') then (found := true; false) else true) (!L) end
        end;
      if !L' = ListMergeSort.sort (fn (x, y) => String.compare (x, y) = GREATER) (!L') then !L' else sort xs
    end
end
"""

ignore = False
input_buf = ""


def input_filter(binp):
    global input_buf

    inp = binp.decode("ascii")
    input_buf += inp

    return binp


def output_filter(bout):
    global ignore, input_buf

    out = bout.decode("ascii")

    if out[-2:] == "- ":
        if input_buf != "":
            inp = input_buf.replace("\n", " ").replace("\r", " ")

            try:
                words = inp.strip(" ").split(" ")
                if words[0] == "sort" and words[-1][-1] == ";":
                    # Can your statically typed language do this?
                    lst = ast.literal_eval(" ".join(words[1:])[:-1])
                    if type(lst) is not list:
                        raise Exception()
                    for x in lst:
                        if type(x) is not float:
                            raise Exception()

                    arg = " ".join([str(x) for x in lst])

                    # We all know functional languages are slow, so do the sorting in C
                    # This is known as an "optimization"
                    res = subprocess.run(["./gottagofast", arg], stdout=subprocess.PIPE)
                    ignore = True
                    return res.stdout + b"\r\n- "
            except:
                pass
            finally:
                input_buf = ""
        elif ignore:
            ignore = False
            return b"- "

    return bout


with tempfile.NamedTemporaryFile(suffix=".sml") as tmp:
    tmp.write(backup_sort)
    tmp.flush()
    with pexpect.spawn("/usr/local/bin/sml", [tmp.name], encoding="ascii") as sml:
        sml.expect_exact("[autoloading done]")
        sml.expect_exact("\n")
        sml.interact(input_filter=input_filter, output_filter=output_filter)
