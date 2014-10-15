# Produce summary plots from the tables generated with writeSummaryTable.r.
#
# Requires gnuplot 4.6. The font path can be set with the environment variable GDFONTPATH.
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

set key reverse Left font ",14" opaque

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



# Fields:
# 1:W 2:St 3:sec 4:SL 5:effS1RPhi 6:effS3RPhi 7:effSeg 8:resHit 9:pullHit 10:meanAngle  11:sigmaAngle 12:meanAngle_pull 13:sigmaAngle_pull 14:meanPos_pull 15:sigmaPos_pull

data=     '"<sort -gs -k 2 sigma_2012D_22jan13_BP7X_noDRR_statByLayer.txt"'
mcobs=    '"<sort -gs -k 2 sigma_DYJetsToLL_M-50_BP7X_noDRR_statByLayer.txt"'
mctrue =  '"<sort -gs -k 2 True_RelValZMM5312_BP7X_noDRR_summary.txt"'


#### Hit Resolution
if (print) {set output "HitReso_phiTheta.png"}
set yrange [100:900]
set ylabel "Hit Resolution [{/Symbol m}m]" offset 0,graph 0.35
plot \
@data using (($3)==1&&int($4)==1?$6*10000:1/0) title '{/Symbol f} SLs, data'      w p pt  5 ps 1.4 lc 4, \
@mcobs using (($3)==1&&int($4)==1?$6*10000:1/0) title '{/Symbol f} SLs, MC'       w p pt  4 ps 1.4 lc 4, \
@mctrue using (($3)==1&&int($4)==1?$8*10000:1/0) title '{/Symbol f} SLs MC Truth' w p pt 4 ps 1.4 lc 3, \
\
@data using (($3)==1&&int($4)==2?$6*10000:1/0) title '{/Symbol q} SLs, data'      w p pt 13 ps 1.5 lc 13, \
@mcobs using (($3)==1&&int($4)==2?$6*10000:1/0) title '{/Symbol q} SLs, MC'       w p pt 12 ps 1.5 lc 13, \
@mctrue using (($3)==1&&int($4)==2?$8*10000:1/0) title '{/Symbol q} SLs MC Truth' w p pt 12 ps 1.5 lc 14


if (print) {set output "HitReso_phi.png"}
set yrange [100:900]
set ylabel "Hit Resolution [{/Symbol m}m]" offset 0,graph 0.35
plot \
@data using (($3)==1&&int($4)==1?$6*10000:1/0) title '{/Symbol f} SLs, data'      w p pt  5 ps 1.4 lc 4, \
@mcobs using (($3)==1&&int($4)==1?$6*10000:1/0) title '{/Symbol f} SLs, MC'       w p pt 13 ps 1.5 lc 3, \
@mctrue using (($3)==1&&int($4)==1?$8*10000:1/0) title '{/Symbol f} SLs MC Truth' w p pt 12 ps 1.5 lc 13


if (print) {set output "HitReso_theta.png"}
set yrange [100:900]
set ylabel "Hit Resolution [{/Symbol m}m]" offset 0,graph 0.35
plot \
@data using (($3)==1&&int($4)==2?$6*10000:1/0) title '{/Symbol q} SLs, data'      w p pt  5 ps 1.4 lc 4, \
@mcobs using (($3)==1&&int($4)==2?$6*10000:1/0) title '{/Symbol q} SLs, MC'       w p pt 13 ps 1.5 lc 3, \
@mctrue using (($3)==1&&int($4)==2?$8*10000:1/0) title '{/Symbol q} SLs MC Truth' w p pt 12 ps 1.5 lc 13
