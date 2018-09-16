Unique class id: fajr
===========================Question 1:==============================

A. NO ERRORS.
B. Builds a BST with no right children.
C. Does not always add a new node.
D. Removes incorrect node(s).
E. Does not always remove node.
F. Structure is right but count is wrong.
G. Violates a fundamental property of BSTs (is backwards).
H. Incorrectly identifies smallest/largest nodes in the tree.
I. Search succeeds when it should not.
J. Total length doesn't sum the lengths of all the nodes' keys.

Answer: G,C,I,A,D,F,J,E,B,H

===========================Question 2:==============================
Analyzing bad bst1:

After running (make testbst2), I noticed two parts of the output which
seem to indicate that the issue lied with making new nodes:

==6529== Invalid read of size 4
==6529==    at 0x10CF8: TestBSTAdd_alphabetBST (in /home/linux/ieng6/
					cs30f/cs30fajr/pa4-jams/testbst2.run)
==6529==  Address 0x0 is not stack'd, malloc'd or (recently) free'd

and

=6529== HEAP SUMMARY:
==6529==     in use at exit: 9,164 bytes in 53 blocks
==6529==   total heap usage: 66 allocs, 13 frees, 9,279 bytes allocated
==6529== 
==6529== 56 (48 direct, 8 indirect) bytes in 4 blocks are definitely lost 
					in loss record 5 of 10
==6529==    at 0x4835770: calloc (vg_replace_malloc.c:566)
==6529==    by 0x127FF: bst_makeNode (in /home/linux/ieng6/cs30f/cs30fajr/
					pa4-jams/testbst2.run)

------end-------
(**valgrind messages shortened so as to not lose points for coding style**)

These valgrind messages seem to indicate that when running my bst_add test
function, when we read memory addresses that were supposed to be properly
allocated, they are not there (ie. Invalid read of size 4). This means that
C. Does not always add a new node makes the most sense for an answer.


Analyzing bad bst6:
After running (make testbst6), I noticed two parts of the output which
seem to indicate that the issue lied with making new nodes:

==7849== 
==7849== HEAP SUMMARY:
==7849==     in use at exit: 400 bytes in 22 blocks
==7849==   total heap usage: 188 allocs, 166 frees, 10,616 bytes allocated
==7849== 
==7849== 144 (4 direct, 140 indirect) bytes in 1 blocks are definitely lost 
			in loss record 3 of 4
==7849==    at 0x4833970: malloc (vg_replace_malloc.c:263)
==7849==    by 0x10B8B: configureAlphabetTestTree (in /home/
			linux/ieng6/cs30f/cs30fajr/pa4-jams/testbst6.run)
==7849== 
==7849== 256 bytes in 1 blocks are definitely lost in loss record 4 of 4
==7849==    at 0x4833970: malloc (vg_replace_malloc.c:263)
==7849==    by 0x118AF: CuStringInit (in /home/
			linux/ieng6/cs30f/cs30fajr/pa4-jams/testbst6.run)
==7849== 
==7849== LEAK SUMMARY:
==7849==    definitely lost: 260 bytes in 2 blocks
==7849==    indirectly lost: 140 bytes in 20 blocks
==7849==      possibly lost: 0 bytes in 0 blocks
==7849==    still reachable: 0 bytes in 0 blocks
==7849==         suppressed: 0 bytes in 0 blocks
==7849== 
==7849== For counts of detected and suppressed errors, rerun with: -v
==7849== ERROR SUMMARY: 2 errors from 2 contexts (suppressed: 0 from 0)
rm testbst6.run

------end-------
(**valgrind messages shortened so as to not lose points for coding style**)

I think for this bst, the structure is right but the nodes are wront and 
the count is wrong. 
