# -*- coding: utf-8 -*-
"""
Created on Tue Feb 14 16:05:16 2023

@author: PGS2KOR
"""

from BMS_parameters_thd import\
    BMS_PARAMETERS_THD, BMS_PARAMETERS_COUNT

from BMS_sensor_simulator import\
    get_simulated_BMS_parameters

from json_format_output_generator import\
    create_json_format_output

def send_packet_to_console(json_bms_paramters):
    print(json_bms_paramters)

def BMS_parameters_sender():
    simulated_battery_parameters = get_simulated_BMS_parameters(BMS_PARAMETERS_THD, BMS_PARAMETERS_COUNT)
    json_bms_paramters = create_json_format_output(simulated_battery_parameters)
    send_packet_to_console(json_bms_paramters)
    return