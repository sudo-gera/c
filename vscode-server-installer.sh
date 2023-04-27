read -p 'What commit of vscode server do you wish to install? ' commit

echo ""

if [ ! -d "$HOME/.vscode-server/bin/$commit" ] ; then
    mkdir -p install-vscode-server
    cd install-vscode-server
<<<<<<< HEAD
    curl -LO https://update.code.visualstudio.com/commit:$commit/server-linux-x64/stable
=======
    wget https://update.code.visualstudio.com/commit:$commit/server-linux-x64/stable
>>>>>>> 409b23bb6e0aba34433d9b534b13fbc7cca76958
    tar -xf stable
    mkdir -p ~/.vscode-server/bin
    mv vscode-server-linux-x64 ~/.vscode-server/bin/$commit
    cd ..
    rm -rf install-vscode-server
    echo "vscode server commit:$commit installed"
else
    echo "Commit already installed"
fi

<<<<<<< HEAD
echo ""
=======
echo ""
>>>>>>> 409b23bb6e0aba34433d9b534b13fbc7cca76958
