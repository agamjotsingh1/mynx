#!/usr/bin/env bash

# requirements:
# 1. smbclient installed
# 2. static ip set on your host to 192.168.2.x subnet

SERVER_IP="192.168.2.99"
SHARE_NAME="xilinx"
SMB_USER="xilinx"
SMB_PASS="xilinx"

show_help() {
    echo "Usage: $0 [upload|download] [local_path] [remote_dir] [remote_path]"
    exit 1
}

if [ "$#" -ne 4 ]; then
    show_help
fi

ACTION=$1
LOCAL_PATH=$2
REMOTE_DIR=$3
REMOTE_PATH=$4

if [ "$ACTION" == "upload" ] && [ ! -f "$LOCAL_PATH" ]; then
    echo "Error: Local file '$LOCAL_PATH' does not exist."
    exit 1
fi

if [ "$ACTION" == "upload" ]; then
    echo "Uploading local file to PYNQ..."
    SMB_COMMAND="mkdir \"$REMOTE_DIR\"; put \"$LOCAL_PATH\" \"$REMOTE_PATH\""
elif [ "$ACTION" == "download" ]; then
    echo "Downloading file from PYNQ to local..."
    SMB_COMMAND="get \"$REMOTE_PATH\" \"$LOCAL_PATH\""
else
    echo "Error: Invalid action. Choose 'upload' or 'download'."
    show_help
fi

smbclient "//$SERVER_IP/$SHARE_NAME" -U "$SMB_USER%$SMB_PASS" -c "$SMB_COMMAND"

if [ $? -eq 0 ]; then
    echo "Success!"
else
    echo "Transfer failed. Check paths, connection, or password."
fi

