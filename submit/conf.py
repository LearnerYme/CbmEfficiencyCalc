class Args:
    logName = '.submit.log'
    fileList = '/u/yige/DataAnalysis/cbm/4p9/0GetList/full.file.list'
    nFilesPerJob = 20
    targetDir = '/lustre/hades/user/yige/4p9/x/eff'
    execName = 'run.sh' # this will be copied
    taskName = 'effCalc'
    cpList = [
        execName,
    ]
    cprList = [
    ]
    lnList = [
        'AnalysisExec'
    ]
