(module
  (func $add (param $a i32) (param $b i32) (result i32)
	get_local $a		;; push param a to stack
	get_local $b		;; push param b to stack
	i32.add)			;; add two numbers in stack, and this value would be returned
  (export "add" (func $add))
)
