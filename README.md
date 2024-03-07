# Efficiency calculation for CBM

Author: Yige Huang

Date: 03.03.2024

Version: 1.0

## Quick start

Based on [AnalysisTemplate v2.1](https://github.com/LearnerYme/AnalysisTemplate).

1. Run `./install.sh`

2. If you want to clean the folder, run `./install.sh uninstall`

3. Copy `build/AnalysisExec` to `submit`

4. Enter `submit`, change details of jobs in `conf.py` and run `python3 manager.py submit`

5. When jobs are all finished, hadd them

6. Run `root -l -b -q GetEffHist.cxx` to generate efficiency file

7. There is also alternative way to save efficiency file, see `FitEffCurve`
    > But one should find a proper fitting function, since the shapes of efficiency in CBM case are not the same, this tool can currently make no use...

## Patch Note

* 03.03.2024 by yghuang v1.0:

> First version.
