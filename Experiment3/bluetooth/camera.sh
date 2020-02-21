#!/bin/bash

raspistill -o cam.jpg
./rfcomm-server
