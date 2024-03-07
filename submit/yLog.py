import logging
r'''
YLOG - a simple logging package
author: yghuang
version: 1.0
date: Oct. 26, 2021
Usage:
    from yLog import yLog
    logger = yLog()
    logger.log(YOUR_TEXT)
'''

class yLog:
    def __init__(self, name:str) -> None:
        self.logger = logging.getLogger()
        self.logger.setLevel(logging.INFO)

        self.hterm = logging.StreamHandler()
        self.hterm.setLevel(logging.INFO)
        self.hfile = logging.FileHandler(name)
        self.hfile.setLevel(logging.INFO)

        self.formatter = logging.Formatter('%(asctime)s %(message)s')

        self.hterm.setFormatter(self.formatter)
        self.hfile.setFormatter(self.formatter)

        self.logger.addHandler(self.hterm)
        self.logger.addHandler(self.hfile)
        return
    
    def log(self, text:str):
        self.logger.info(text)
        return
