# Produce summary plots from the tables generated with writeSummaryTable.r.
#
# Requires gnuplot 4.6.
#

reset
set macro

#Set this to 1 to print plots to png files
print=0

# Output to png viewer
set terminal png enhanced font "Arial,14" size 1000,750
set output '| display png:-'


######################################################################
set pointsize 1
set grid

set key reverse Left font ",14" opaque box

theta=0
phi=1

set arrow 2 from 180-18,graph 0 to 180-18,graph 1 nohead  back lt 1 lc -1 lw 1
set arrow 3 from 360-18,graph 0 to 360-18,graph 1 nohead  back lt 1 lc -1 lw 1
set arrow 4 from 540-18,graph 0 to 540-18,graph 1 nohead  back lt 1 lc -1 lw 1

#set arrow 2 from 180,graph 0 to 180,graph 1 nohead  back lt 22 lw 1
#set arrow 3 from 360,graph 0 to 360,graph 1 nohead  back lt 22 lw 1
#set arrow 4 from 540,graph 0 to 540,graph 0.85 nohead  back lt 22 lw 1

set xtics ("W-2 MB1" 0, "W-1" 36, "W0" 72, "W1" 108, "W2" 144, \
           "W-2 MB2" 180, "W-1" 216, "W0" 252, "W1" 288, "W2" 324, \
           "W-2 MB3" 360, "W-1" 396, "W0" 432, "W1" 468, "W2" 504, \
           "W-2 MB4" 540, "W-1" 568, "W0" 596, "W1" 624, "W2" 652) ;\
#set xrange[0:]
set xrange[-18:668]
set xtics rotate by -45


set label 1 "MB1" at  72,graph 0.05 center
set label 2 "MB2" at 252,graph 0.05 center
set label 3 "MB3" at 432,graph 0.05 center
set label 4 "MB4" at 596,graph 0.05 center


######################################################################

sl=phi
#sl=theta

if (sl==theta) unset arrow 4

#ymin=-6000
#ymax=8000

#ymin = -50
#ymax=100

ymin = -50
ymax=150


min(x,y) = x<y?x:y
max(x,y) = x>y?x:y
clip(x) = max(min(x,ymax),ymin)

vdrift=54.3

# 2015Dv3
file = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015D_ttrig_256675_vDrift_259626_chamberByView.txt"'


#Full 2015Dv4
file0 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_chamberByView.txt"'

# Only run 258443-25844
file1  = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_run258443-258445_chamberByView.txt"'
file4 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_until258442_chamberByView.txt"'
file5 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_since258446_chamberByView.txt"'

#Recalibrated runs 258443-258445
#file3 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_corrRun258443-258445_vDrift_259626_raw_chamberByView.txt"'



set yrange [ymin:ymax]
if (print) {set output "residual_2015Dv4.png"}
set ylabel "Resudial [{/Symbol m}m]" offset 0,graph 0.35


plot \
@file  using (int($4)==1?clip($7*10000):1/0) title '{/Symbol f} SL- run 256629-258157'  w p pt 5 ps 0.7 lc 2, \
@file4 using (int($4)==1?clip($7*10000):1/0) title '{/Symbol f} SL- run 258159-258442'  w p pt 6 ps 0.7 lc 1, \
@file5 using (int($4)==1?clip($7*10000):1/0) title '{/Symbol f} SL- run 258446-258750'  w p pt 8 ps 0.7 lc 7


q


