
//Lomuto Partitioning Scheme
//  short *partition(short *begin, short *end) {
//  short pivot = *(end-1) ;
//  short *i=begin-1 ;
//  for(short *j=begin;j<end;++j) {
//    if(*j <= pivot) {
//      i++ ;
//      std::swap(*i,*j) ;
//    }
//  }
//  return i ;
//}


//First we will define the partition function.
//First We will push the frame seen above. It takes 2 arguments and 3 locals. 
(PARTITION)
$pushFrame 2 3
=partition.begin 0
=partition.end 1
=partition.pivot 0
=partition.i 1
=partition.j 2

// int *PARTITION(int *begin, int *end) {

//   pivot = *(end-1);
//Below implements end - 1
$getArgument partition.end
D=D-1
//Next we push the value and call get pointer to get *(end-1). 
$pushD
$getPTR
//Set pivot to *(end-1)
$setLocal partition.pivot

//   *i = begin - 1
$getArgument partition.begin
D=D-1
$setLocal partition.i

//   for(*j=begin;j<end;j++) {
$getArgument partition.begin
$setLocal partition.j

//After we set j equal to begin, we enter the loop. 
//First we check if j is less than end. If so, we move to the next instruction.
(LOOP1)
$getLocal partition.j
$pushD
$getArgument partition.end
$pushD
$lt
$popAD
@LOOP1EXIT
D;JEQ
 
//Next we get pointer j, and check if it less than or equal to pivot.
//I implement mine by doing greater than, then not the value. 
//     if(*j <= pivot) {
$getLocal partition.j 
$pushD
$getPTR
$getLocal partition.pivot
$pushD
$gt
$not
$popAD

//If *j is greater pivot, we will exit the if statement.
@IFEXIT
D;JEQ

//If *j was less than or equal to pivot, we increment i by 1 and swap the values. 
//        i = i + 1
$getLocal partition.i
D=D+1
$setLocal partition.i

// I implement my swap function using stack operations. 
//        swap(*i,*j) ;

$getLocal partition.i
$pushD
$getPTR

$getLocal partition.j
$pushD
$getPTR

$getLocal partition.i
$pushD
$setPTR

$getLocal partition.j
$pushD
$setPTR

//     }
(IFEXIT)
//   }

//This implements j++ in the for loop 
$getLocal partition.j
D=D+1
$setLocal partition.j

@LOOP1
0;JMP

(LOOP1EXIT)

//   return i ;
$getLocal partition.i
$setArgument 0
$popFrame 2 3
$return
// }




//short qsort(short *begin, short *end) {
//  short sz = end-begin ;
//  short *split ;
//  if(sz < 2)
//    return sz ;
//  split = partition(begin,end) ;
//  qsort(begin,split) ;
//  qsort(split,end) ;
//  return sz;
//}

//First we push the frame. In the code above, we see that qsort has 2 arguments and 2 locals.
(QSORT)
$pushFrame 2 2
=qsort.begin 0
=qsort.end 1
=qsort.sz 0
=qsort.split 1

//  short sz = end-begin ;
$getArgument qsort.end
$pushD
$getArgument qsort.begin
$pushD
$sub
$popAD
$setLocal qsort.sz

//  if(sz < 2)
$getLocal qsort.sz
$pushD
//To get 2, we will load the address 2 into the data register 
@2
D=A
$pushD
$lt
$popAD

//If sz greater than 2, we will go to the IFLOOPEXIT label to continue
@IFLOOPEXIT
D;JEQ

//If sz was less than 2, we will just return sz. 
$getLocal qsort.sz
$setArgument 0
$popFrame 2 2
$return 

(IFLOOPEXIT)
//  split = partition(begin,end) ;
$getArgument qsort.begin
$pushD
$getArgument qsort.end
$pushD
$procedureCall 2 PARTITION
$popAD
$setLocal qsort.split

//The following will recursively call on QSORT. 
//  qsort(begin,split) ;
$getArgument qsort.begin
$pushD
$getLocal qsort.split
$pushD
$procedureCall 2 QSORT
$popAD

//The following will recursively call on QSORT.
//  qsort(split,end) ;
$getLocal qsort.split
$pushD
$getArgument qsort.end
$pushD
$procedureCall 2 QSORT
$popAD

//  return sz;
$getLocal qsort.sz
$setArgument 0
$popFrame 2 2
$return
