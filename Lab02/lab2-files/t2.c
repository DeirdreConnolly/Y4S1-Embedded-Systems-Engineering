fred(){
int i,j=0;
i=0;
j=0;
while (i<10){
   if (i&1)
      j=j+i+10;
   i=i+1;
}
return j;
}
