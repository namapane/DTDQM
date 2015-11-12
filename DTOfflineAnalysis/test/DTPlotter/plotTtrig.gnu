# Produce summary plots from the tables generated with writeSummaryTable.r.
#
# Requires gnuplot 4.6.
#

reset
set macro

#Set this to 1 to print plots to png files
print=1

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

min(x,y) = x<y?x:y
max(x,y) = x>y?x:y
#clip(x) = max(min(x,8000),-6000)
clip(x) = max(min(x,200),-100)

vdrift=54.3

#file = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_chamberByView.txt"'
#file2 = '"<sort -gs -k 2 -k 1 ttrig_ZMu_2015Dv4_ttrig_258443_vDrift_259626_run258443-258445_chamberByView.txt"'
file = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_run258443-258445_chamberByView.txt"'
#file2 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_vDrift_259626_run258443-258445_chamberByView_corr.txt"'
file2 = '"<sort -gs -k 2 -k 1 -k 3 ttrig_ZMu_2015Dv4_ttrig_256675_corrRun258443-258445_vDrift_259626_raw_chamberByView.txt"'

#set yrange [-100:200]
if (print) {set output "residual_run258443-258445_zoom.png"}
set ylabel "Resudial [{/Symbol m}m]" offset 0,graph 0.35

plot \
@file using (int($4)==1?clip($7*10000):1/0) title '{/Symbol f} SL- run 258443-258445'  w p pt 5 ps 1 lc 1, \
@file2 using (int($4)==1?clip($7*10000):1/0) title '{/Symbol f} SL - rrecalibrated'  w p pt 2 ps 1.4 lc 7


q


