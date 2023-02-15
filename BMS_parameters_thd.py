# -*- coding: utf-8 -*-
"""
Created on Tue Feb 14 15:29:35 2023

@author: PGS2KOR
"""
BMS_PARAMETERS_THD = {
    'Temperature' : {'max': 45, 'min': 25, 'type': 'int'},
    'soc': {'max': 100, 'min': 0, 'type': 'int'},
    'charging_rate': {'max': 1, 'min': 0, 'type': 'float'}
    }

BMS_PARAMETERS_COUNT = 50