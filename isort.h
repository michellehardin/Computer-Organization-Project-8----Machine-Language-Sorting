// insertion sort
//short isort (short *begin, short *end) {
//  short *i = begin ;
//  short *j ;
//  short x ;
//  while(i<end) {
//    x = *i ;
//    j = i-1 ;
//    while(j>=begin && *j>x) {
//      *(j+1) = *j ;
//      j=j-1 ;
//    }
//    *(j+1) = x ;
//    i=i+1 ;
//  }
//  return end-begin ;
//}


(ISORT)

//int isort (int *begin, int *end) {
$pushFrame 2 3
=ISORT.begin 0
=ISORT.end 1
=ISORT.i 0
=ISORT.j 1
=ISORT.x 2

//  int *i = begin ;
$getArgument ISORT.begin
$setLocal ISORT.i



//  int *j ;

//  int x ;


//  while(i<end) {
(ISORT.LOOP1)
$getLocal ISORT.i
$pushD
$getArgument ISORT.end
$pushD
$lt
$popAD
@ISORT.LOOP1EXIT
D;JEQ


//    x = *i ;
$getLocal ISORT.i
$pushD 
$getPTR
$setLocal ISORT.x


//    j = i-1 ;
$getLocal ISORT.i
D=D-1
$setLocal ISORT.j


//    ** NOTE semantics here! the && operator will prevent the execution
//    ** of the *j>x part of the expression, this is not just a logical
//    ** operation! 
//    while(j>=begin && *j>x) {
(ISORT.LOOP2)
$getLocal ISORT.j
$pushD
$getArgument ISORT.begin 
$pushD
$lt
$not
$popAD
@ISORT.LOOP2EXIT
D;JEQ

$getLocal ISORT.j 
$pushD
$getPTR
$getLocal ISORT.x
$pushD
$gt
$popAD
@ISORT.LOOP2EXIT
D;JEQ 

//      *(j+1) = *j ;
//To set pointer,

$getLocal ISORT.j
$pushD
$getPTR
$getLocal ISORT.j
D=D+1
$pushD
$setPTR


//      j=j-1 ;
$getLocal ISORT.j
D=D-1
$setLocal ISORT.j

@ISORT.LOOP2
0;JMP
//    }		//END OF LOOP2EXIT

(ISORT.LOOP2EXIT)
//*(j+1) = x ;
$getLocal ISORT.x
$pushD
$getLocal ISORT.j
D=D+1
$pushD
$setPTR

//    i=i+1 ;
$getLocal ISORT.i
D=D+1
$setLocal ISORT.i


@ISORT.LOOP1
0;JMP


(ISORT.LOOP1EXIT)
//  }	//End of LOOP1EXIT


//  return end-begin ;
$getArgument ISORT.end 
$pushD
$getArgument ISORT.begin
$pushD
$sub
$popAD	//should have end-begin in this. 
$setArgument 0
$popFrame 2 3
$return
// }

