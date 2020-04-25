#!/bin/bash

USER=$(id -un)
curl -s "http://moss.cs.iit.edu:35101/?username=$USER&usermail=$USER@hawk.iit.edu&submit=Submit" | tar xvf - 
