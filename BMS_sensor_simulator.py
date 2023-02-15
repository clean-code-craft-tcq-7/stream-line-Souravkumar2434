# -*- coding: utf-8 -*-
"""
Created on Tue Feb 14 15:22:16 2023

@author: PGS2KOR
"""



import random


def simulate_values_for_BMS_parameters(parameter, count):
    param_values = []
    if parameter['type'] == 'int':
        param_values = simulate_values_for_int_type_BMS_parameters(parameter, count)
    elif parameter['type'] == 'float':
        param_values = simulate_values_for_float_type_BMS_parameters(parameter, count)
    return param_values


def simulate_values_for_int_type_BMS_parameters(parameter, count):
    return [random.randint(parameter['min'], parameter['max'])\
            for _ in range(count)]


def simulate_values_for_float_type_BMS_parameters(parameter, count):
    return [round(random.uniform(parameter['min'], parameter['max']), 1)\
            for _ in range(count)]


def get_simulated_BMS_parameters(bms_params_thd, bms_params_count):
    battery_parameters = {}
    for key in bms_params_thd.keys():
        battery_parameters[key] = simulate_values_for_BMS_parameters(bms_params_thd[key], bms_params_count)
    return battery_parameters

