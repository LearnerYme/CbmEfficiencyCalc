# Duplicated particle remover

Author: Yige Huang

Date: 28.02.2024

Version: 1.0

## Quick start

1. copy this folder to `analysis/src` (something like this)

2. in your MC particle loop of analysis, call `DuplicateRemover::Make(AnalysisTree::Particle)` and only use this MC particle when it returns `false`

3. add `DuplicateRemover` into `CMakeList.txt`'s `ADD_TOOLS` as anyother modules

4. compile and run

## Patch note

28.02.2024 by yghuang (v1.0):

* First version
