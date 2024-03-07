#!/bin/bash

#SBATCH --partition=debug
#SBATCH --nodes=1
#SBATCH --output=log.output.txt
#SBATCH --error=log.error.txt
#SBATCH --job-name=__TASKNAME__

./AnalysisExec
