.name "zork"
.comment "just a basic living prog"

labeliwi: 	sti r1,%:live,%1
	and	r1,%0,r1
st r1,r1
live:	live %:live
		zjmp %:live
