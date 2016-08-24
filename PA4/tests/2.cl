(*class Object inherits CC__ {
};

class CC__ inherits CC__ {
};
class D {
};


class CC__ inherits Int {
};

class D {
ana(): Int {
(let x:Int <- 1, y:Int <-3 in 2)+3
};
};
*)

class M inherits M {
};

class F inherits E {
};

class G inherits F {
};

class E inherits G {
};


class C {
	a : Int;
	b : Bool;
	init(x : Int, y : Bool) : C {
           {
		a <- x;
		b <- y;
		self;
           }
	};
};

(*
class SELF_TYPE {
};
*)
Class Main {
	main():C {
	  (new C).init(1,true)
	};
};
