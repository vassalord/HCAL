# HcalTupleAnalyzer
This code is to analyze the output of HcalTupleMaker. 
You should add your own analysis to the `macros/` folder, or use any of the already existing ones if they are sufficient for you, and run it with `run.py`

Simple Usage: When you have only one type of input files in your analysis
```
python run.py macros/analysisClass_Everything.C config/input_lists/utca_input.txt config/tree_lists/treelist.txt output.root
```
The first argument is the macro file you want to run.
The second argument is a list containing all input files (outputs from HcalTupleMaker). Can also define multiple inputs here, see `config/input_lists/main_input.txt` as an example.
The third argument is another list, specifying the structure of the tree in the inputs. The default `config/tree_lists/treelist.txt` should be always sufficient, unless you changed something in your input files.
The last argument is the output filename.

The output will contain histograms created by the macro. To make a directory full of `.png` files instead, run one of the scripts in the `plot_macros/` folder, such as:
```
python3 plot_macros/plot_Custom.py -i output.root -o output_plots/
```
specifying the input root file (output from previous step) and output directory.
