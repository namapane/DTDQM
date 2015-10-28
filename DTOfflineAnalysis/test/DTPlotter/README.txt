### Granularities:
StatBy*    : w,st,0,0
ChamberBy* : w,st,se,0 
SL         : w,st,se,sl


### Observed quantities: workflow

1. Produce trees
cf ../fillTree 

2. Produce a .root file with plots: 
readTree.r

3. Plotting scripts:

plot.r 
Residual plots and correlations for a given chamber.

plot8l.r 
Plot alignment residuals for all phi layers in a chamber.

plot12l.r
Compare a given plot for the 12 sectors of a given W/S

4. Table scripts::


### True quantities

plotValidation.r
plot true residuals and pulls (from files produced in Validation/DTRecHits package)


-------



fillTTrigTable.r
Prepare table with residuals (=calibration)

plotAllSigma.r
Prepare table with observed resolutions 

plotAllLR.r
Prepare table with alignment factors. 

plotLayerAli.r
Plot distribution of alignment corrections.


plot12s.r

plotAllVd.r

plotPull.r

plotThetaProblem.r

primo.r


plotLayerAli
