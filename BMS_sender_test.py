# -*- coding: utf-8 -*-
"""
Created on Mon Feb 13 15:12:22 2023

@author: PGS2KOR
"""
from BMS_parameters_thd import\
    BMS_PARAMETERS_THD, BMS_PARAMETERS_COUNT

from BMS_sensor_simulator import\
    get_simulated_BMS_parameters,simulate_values_for_BMS_parameters

from create_sender_output import\
     BMS_parameters_sender, send_packet_to_console

from json_format_output_generator import create_json_format_output


import unittest
from unittest.mock import patch

class Test_BMS_sender(unittest.TestCase):
    #This test case is to test the functionality of getting the simulated BMS parameters
    @patch('BMS_sensor_simulator.simulate_values_for_BMS_parameters')
    def test_get_simulated_BMS_parameters(self, mock_bms_parameters):
        mock_bms_parameters.return_value = [1]
        self.assertEqual(get_simulated_BMS_parameters(BMS_PARAMETERS_THD, BMS_PARAMETERS_COUNT), {'Temperature': [1], 'soc': [1], 'charging_rate':[1]})
    
    #This test case is to test the functionality of refactored get_simulated_BMS_parameters for each parameter
    @patch('BMS_sensor_simulator.simulate_values_for_int_type_BMS_parameters')
    def test_simulate_values_for_int_type_BMS_parameters(self, mock_bms_parameter):
        test_para = {'max': 45, 'min': 25, 'type': 'int'}
        mock_bms_parameter.return_value = [1]
        self.assertEqual(simulate_values_for_BMS_parameters(test_para, 50), [1])

    #This test case is to test the functionality of refactored get_simulated_BMS_parameters for each parameter
    @patch('BMS_sensor_simulator.simulate_values_for_float_type_BMS_parameters')
    def test_simulate_values_for_float_type_BMS_parameters(self, mock_bms_parameter):
        test_para = {'max': 1, 'min': 0, 'type': 'float'}
        mock_bms_parameter.return_value = [1]
        self.assertEqual(simulate_values_for_BMS_parameters(test_para, 50), [1])


    #This test case is to test the functionality of getting the json format of BMS parameters
    @patch('json_format_output_generator.create_json_format_output')
    def test_create_json_format_output(self, mock_create_json_format):
        mock_create_json_format.return_value = '{"data": []}'
        self.assertEqual(create_json_format_output([]),'{"data": []}')
    #This test case is to test the functionality of sending the output to console
    def test_send_packet_to_console(self):
        with patch('builtins.print') as mock_print:
            send_packet_to_console("Hello")
            mock_print.assert_called_once_with('Hello')

if __name__ == '__main__':
    unittest.main()