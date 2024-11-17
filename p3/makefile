

JC = javac
J = java

Visual2.class: Memory.class Visual2.java 
	$(JC) Visual2.java

Memory.class: Process.class Partition.class Visual.class Memory.java 
	$(JC) Memory.java

Partition.class:  Partition.java
	$(JC) Partition.java

Process.class:  Process.java
	$(JC) Process.java

Visual.class:  Visual.java
	$(JC) Visual.java


run:
	make
	$(J) Visual2
