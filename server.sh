#!/bin/bash

# Get the current username dynamically
USER_HOME="/home/$USER"

# Navigate to the project directory
cd "$USER_HOME/Workspace/Project/GoogleMap/" || { echo "Directory not found"; exit 1; }

# Start the Python HTTP server in the background and log output
nohup python3 -m http.server 8081 --bind 0.0.0.0 &

# Check if the server started successfully
if [ $? -eq 0 ]; then
  echo "HTTP server started successfully on port 8080."
  # Open the index.html in the default browser
  xdg-open "http://localhost:8081/index.html"
else
  echo "Failed to start the HTTP server."
  exit 1
fi

