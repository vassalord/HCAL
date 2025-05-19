import os
import ROOT
from PlotParser import parser

ROOT.gROOT.SetBatch(ROOT.kTRUE)

args = parser.parse_args()

inFileName = args.inputPath
outFileName = args.outputPath
FileType = "png"

inputFile = ROOT.TFile(inFileName,"READ")
histNames = [k.GetName() for k in inputFile.GetListOfKeys()]

print("Total Number of Hist: %s"%len(histNames))
if not os.path.isdir(outFileName): os.makedirs(outFileName)
if not outFileName.endswith("/"): outFileName = outFileName+"/"
c = ROOT.TCanvas()
#c.Print(outFileName+"[")
for i,histn in enumerate(histNames):
  hist = inputFile.Get(histn)
  hist.SetStats(0)
  if hasattr(hist, "GetZaxis"):
    hist.GetZaxis().SetLabelSize(0.026) # Default 0.035
  hist.Draw("colz")
  hname = hist.GetName().replace(" ", "_")
  for t in FileType.split(","):
    c.SaveAs(outFileName+hname+"."+t)
  #c.Print(outFileName)
#c.Print(outFileName+"]")
