Notes:
I've added a branch that contains no helper code other than what comes with UE5 and set it to default.
The no helper code is under the no-helper branch with the helper code being under the main branch.

//-----------------------------------------------------

This plugin has a dependency on another - UE5ShaderUtils
You find it here: https://github.com/RyanSweeney987/UE5ShaderUtils

Git:
In your plugin folder run the following: git clone https://github.com/RyanSweeney987/UE5ShaderUtils

Download:
Open the repo, click on the green "<> code" button and click on the "Download ZIP" option.
When downloaded, extract the contents into the plugin folder, ensuring the following hierarchy:

./Plugins/UE5ShaderUtils/....
With files such as UE5ShaderUtils.uplugin inside the UE5ShaderUtils folder
