usage = r'''
    #-------------------------------------------------------#
    # Job submit system for GSI slurm.                      #
    # Version: vanilla                                      #
    # Patch: 2.0                                            #
    # Author: Yige Huang                                    #
    # Date: 15.02.2024                                      #
    #-------------------------------------------------------#
    # Usage                                                 #
    # python3 manager.py $CMD                               #
    # - CMD can be 'submit', 'resubmit', 'clean' or 'report'#
    # - also 'sub', 're', 'cla' or 'repo'                   #
    #-------------------------------------------------------#
'''

import os
import sys
from conf import Args
from yLog import yLog

l = yLog(Args.logName)
l.log(f'Job l info. can be found in {Args.logName}')

if len(sys.argv) != 2:
    l.log('[ERROR] Arguments invalid.')
    print(usage)
    exit()
else:
    mode = sys.argv[1]
    if mode in ['submit', 'sub', 'resubmit', 're', 'clean', 'cla', 'report', 'repo']:
        l.log(f'[LOG] Current mode is {mode}.')
    else:
        l.log('[ERROR] Arguments invalid.')
        print(usage)
        exit()

if Args.execName not in Args.cpList and Args.execName not in Args.lnList:
    l.log(f'[ERROR] The executable target {Args.execName} is not in the lists of copy or symlink.')
    exit()

if mode in ['submit', 'sub']:
    fileList = Args.fileList
    files = [item.rstrip('\n') for item in open(fileList, 'r').readlines()]
    nFiles = len(files)
    nFilesPerJob = Args.nFilesPerJob
    nJobs = nFiles // nFilesPerJob
    bonus = nFiles - nJobs*nFilesPerJob
    l.log(f'[LOG] Full file list: {fileList}')
    l.log(f'[LOG] In total {nFiles} files will be split into {nJobs} jobs, {nFilesPerJob} files will be despatched into each of them.')
    if bonus != 0:
        l.log(f'[LOG] And a bonus job will handle {bonus} files.')

    targetDir = Args.targetDir
    l.log(f'[LOG] Now creating job directories in {targetDir}.')
    for i in range(nJobs):
        os.mkdir(f'{targetDir}/job{i}')
    if bonus != 0:
        os.mkdir(f'{targetDir}/job{nJobs}')

    l.log(f'[LOG] Now preparing.')
    for idx in range(nJobs):
        srt = f'{targetDir}/job{idx}'
        with open(f'{srt}/file.list', 'w') as f:
            for iFile in range(idx*nFilesPerJob, (idx+1)*nFilesPerJob):
                f.write(f'{files[iFile]}\n')
        for lnItem in Args.lnList:
            os.system(f'ln -s {os.getcwd()}/{lnItem} {srt}/{lnItem}')
        for cpItem in Args.cpList:
            os.system(f'cp {os.getcwd()}/{cpItem} {srt}/{cpItem}')
        os.system(f'cp {Args.execName} {srt}/{Args.execName}')
        os.system(f'sed -i "s/__TASKNAME__/{Args.taskName}_{idx}/g" {srt}/{Args.execName}')
        for cprItem in Args.cprList:
            os.system(f'cp -r {os.getcwd()}/{cprItem} {srt}/{cprItem}')
    if bonus:
        srt = f'{targetDir}/job{nJobs}'
        with open(f'{srt}/file.list', 'w') as f:
            for iFile in range(nJobs*nFilesPerJob, nFiles):
                f.write(f'{files[iFile]}\n')
        for lnItem in Args.lnList:
            os.system(f'ln -s {os.getcwd()}/{lnItem} {srt}/{lnItem}')
        for cpItem in Args.cpList:
            os.system(f'cp {os.getcwd()}/{cpItem} {srt}/{cpItem}')
        for cprItem in Args.cprList:
            os.system(f'cp -r {os.getcwd()}/{cprItem} {srt}/{cprItem}')

    l.log(f'[LOG] Now submitting.')
    if bonus != 0:
        nJobs += 1
    for idx in range(nJobs):
        os.system(f'cd {targetDir}/job{idx} && sbatch {Args.execName}')
        l.log(f'[LOG] - Job {idx+1} of {nJobs} submitted.')

    l.log('[LOG] All finished!')

if mode in ['resubmit', 're']:
    fileList = Args.fileList
    files = [item.rstrip('\n') for item in open(fileList, 'r').readlines()]
    nFiles = len(files)
    nFilesPerJob = Args.nFilesPerJob
    nJobs = nFiles // nFilesPerJob
    bonus = nFiles - nJobs*nFilesPerJob

    targetDir = Args.targetDir

    l.log(f'[LOG] Now scanning target directory.')

    if bonus != 0:
        nJobs += 1
    l.log(f'[LOG] There will be {nJobs} jobs.')

    for idx in range(nJobs):
        os.system(f'cd {targetDir}/job{idx} && sbatch {Args.execName}')
        l.log(f'[LOG] - Job {idx+1} of {nJobs} submitted.')

    l.log('[LOG] All finished!')

if mode in ['clean', 'cla']:
    targetDir = Args.targetDir
    l.log(f'[LOG] Clean directory: {targetDir}. Please confirm with safe code:')
    scode = input()
    if scode != 'CONFIRM':
        l.log('[LOG] Safe code incorrect.')
        exit()
    else:
        os.system(f'rm -rf {targetDir}/job*')
        l.log('[LOG] Clean command finished.')

if mode in ['report', 'repo']:
    fileList = Args.fileList
    files = [item.rstrip('\n') for item in open(fileList, 'r').readlines()]
    nFiles = len(files)
    nFilesPerJob = Args.nFilesPerJob
    nJobs = nFiles // nFilesPerJob
    bonus = nFiles - nJobs*nFilesPerJob
    targetDir = Args.targetDir

    l.log(f'[LOG] Report of this task:')
    if not os.path.exists(fileList):
        l.log(f'[LOG] - The file list does not exist ({fileList})')
        exit()
    if not os.path.exists(targetDir):
        l.log(f'[LOG] - The target direcotry does not exist ({targetDir})')
        exit()

    l.log(f'[LOG] - File list: {fileList}')
    if bonus != 0:
        l.log(f'[LOG] - {nFilesPerJob} x {nJobs} + {bonus} = {nFiles}. In total {nJobs+1} jobs for this issue.')
    else:
        l.log(f'[LOG] - {nFilesPerJob} x {nJobs} = {nFiles}. In total {nJobs} jobs for this issue.')
    
    if os.path.exists(f'{targetDir}/job0'):
        l.log(f'[LOG] - Jobs already submitted, please check the queue of jobs for the status.')
    else:
        l.log(f'[LOG] - Jobs not submitted yet or the outputs have been removed.')
    
    l.log(f'[LOG] - The target path: {targetDir}')
