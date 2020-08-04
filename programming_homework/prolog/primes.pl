check_prime(N, D) :- D * D > N, !; mod(N, D) =\= 0, D1 is D + 1, check_prime(N, D1).
prime(N) :- N > 1, check_prime(N, 2).
composite(N) :- not prime(N).

prime_divisors(1, []) :- !.
prime_divisors(N, Divisors) :- \+ var(N), N > 1, fill_divisors(N, Divisors, 2), !.
fill_divisors(N, [H], _) :- prime(N), H is N, !.
fill_divisors(N, [H | T], D) :- 
	D * D =< N, !,
	((mod(N, D) =:= 0, prime(D), H is D, N1 is div(N, D), fill_divisors(N1, T, D));
		(D1 is D + 1, fill_divisors(N, [H | T], D1))).

prime_divisors(N, Divisors) :- var(N), check(Divisors), multiply(N, Divisors), !.
check([]) :- !.
check([H]) :- prime(H), !.
check([H | T]) :- check(1, H, T), !.
check(A, Now, [H | T]) :- Now =< H, prime(Now), NA is A * Now, check(NA, H, T), !.
check(A, Now, []) :- prime(Now).
multiply(Result, []) :- Result is 1.
multiply(Result, [H | T]) :- number(H), multiply(R1, T), Result is H * R1.