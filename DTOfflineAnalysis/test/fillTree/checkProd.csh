#!/bin/tcsh
# Search for missing root files
# parameter to be specified: production path

#set echo 

set basename=$1

foreach chunk ( *Chunk* )
 set fail="false"


 # Check that root file is existing and not empty
 set filename=${chunk}/DTLocalReco.root
 if ( ! -e $filename ) then
#   echo "Missing root file in " ${chunk}
   set fail="true"
 else if ( -z $filename ) then
#   echo "Empty file: " $filename
   set fail="true"
 endif
 
# if ( $fail == "true" ) then
#   if ( -e ${filename}.recovered ) echo "   found: " ${filename}.recovered
#   if ( -e ${filename}.corrupted ) echo "   found: " ${filename}.corrupted
# else
#   set exitstatus=`grep "2012 with exit status" ${chunk}/*.txt | awk '{print $NF}'`
#   if ( $exitstatus != 0 ) then

 # Check job exit status
 set exitStatus = 0
 if ( -es ${chunk}/exitStatus.txt ) then
   set exitStatus=`cat ${chunk}/exitStatus.txt`
   set fail="true"     
 endif

 # Archive succesful jobs, or report failure
 if ( $fail == "true" ) then
  mkdir -p FAILED
  mv $chunk FAILED/
  set description=""
   if ( $exitStatus == 0 )  set description="(unknown)"
   if ( $exitStatus == 84 ) set description="(missing input file)"
   if ( $exitStatus == 134 ) set description="(Crashed)"
   if ( $exitStatus == 152 ) set description="(Exceeded CPU time)"
   echo $chunk ": failed, exit status = " $exitStatus $description
 endif
end

set scriptpath=`dirname $0`
echo $PWD
${scriptpath}/makeFileList.csh .

# cd -
#end
