DURABILITY=true and MMAP=true
Server Started
CREATE TABLE t1(f1 int,f2 char(15));
Server Killed
Server Started
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	1000	
	
Durability Works Fine
I-Pass Test over
Server Killed
DURABILITY=true and MMAP=true
Server Started
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	1000	
	
Durability Works Fine
II-Pass Test over
Server Killed
Server Started
---------------------------------------------------------
	COUNT(*)	
---------------------------------------------------------
	2000	
	
Durability Works Fine
III-Pass Test over
