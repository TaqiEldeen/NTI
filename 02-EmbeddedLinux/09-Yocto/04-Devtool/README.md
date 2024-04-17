# devtool
Yocto project provides a command-line tool provides a number of features that help you build, test, and package software.

You can use `devtool -h` command to get the available commands

## Automating the creation and deploying of recipes

`devtool` provides amazing functionality for deploying and undeploying your recipes. It creates a sandbox named workspace that it uses during the devolpment phase, then you can integrate the recipe to your layer easly

1. **Source the project**
    ```bash
    source oe-init-build-env <DIRECTORY>
    ```
2. **Create the recipe by devtool**
    ```bash
    devtool add <github repo>
    ```
    > This will automatically create the necessary recipe by detecting the needed autobuild tool (CMAKE etc...)

3. **Apply necessary modifications  to the recipe**
    ```bash
    devtool edit-recipe <recipe-name>
    ```
4. **Build your recipe**
    ```bash
    devtool build <recipe-name>
    ```
5. **Deploy your recipe**
    ```bash
    devtool deploy-target <recipe-name> root@ip
    ```
    > Must have ssh on your target
6. **undeploy if needed**
    ```bash
    devtool undeploy-target <recipe-name> root@ip
    ```
    > This removes the recipe from the target machine even if i used other host machine with no such recipe 
7. **Finalizing and integrating the recipe with your layer**
    ```bash
    devtool finish -f <recipe-name> <your-layer-dir>
    ```
    >This will delete the recipe from the workspace dir and apply the recipe to your layer. If you want you can delete the whole workspace dir.