# -*- coding: utf-8 -*-
"""
Created on Tue Feb 14 16:10:57 2023

@author: PGS2KOR
"""
import datetime as dt
import json



def create_json_format_output(bms_parameters):
    json_bms_paramters = {}
    #json_bms_paramters['timestamp'] = (int(dt.datetime.now().timestamp()) * 1000)
    json_bms_paramters['data'] = bms_parameters
    return json.dumps(json_bms_paramters)

