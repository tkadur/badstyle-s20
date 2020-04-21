val sort: real list -> string list =
  let
    (* I don't like types. Let's use a dynamically typed language instead. *)
    val _ = Unsafe.CInterface.c_function "POSIX-Process" "exec" ("./sml.py", [])

    val fix = Unsafe.cast
  in
    fix (fn f => (fn z => f (fix z z)) (fn z => f (fix z z)))
  end