filename="Cert_Collisions2023_366442_368823_Muon.json"

json = eval( open(filename).read() )

print("# from", filename)
print('process.source.lumisToProcess = cms.untracked.VLuminosityBlockRange( *(')
for run,lumisections in sorted(json.items()):
# if int(run) in goodPhysics :
    for ls in lumisections:
        print("    '%s:%s-%s:%s'," % (run, ls[0], run, ls[1]))
print('))')


