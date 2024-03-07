# Index constants tool

Author: Yige Huang

Date: 28.02.2024

Version: 1.0

## Quick start

1. copy this folder to `analysis/src` (something like this)

2. in your analysis, when you need to use something like `GetField<int>(INDEX)`, directly typei index name here, for example, `McParticle.GetField<int>(IdxSimMotherId)`
    > Note that, you should be aware of the index list avaliable by viewing `IdxConstants.h`

3. add `IdxConstants` into `CMakeList.txt`'s `ADD_TOOLS` as anyother modules

4. compile and run

## Patch note

28.02.2024 by yghuang (v1.0):

* First version
