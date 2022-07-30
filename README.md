# hydrausb3_fw
hydrausb3_fw contains open source (see LICENSE) test firmware / examples / libraries with drivers for HydraUSB3 board using WCH CH569W MCU.

All examples with name HydraUSB3_DualBoard_XXX requires 2x HydraUSB3 v1 boards to be plugged together.
* First HydraUSB3 board shall have PB24 not populated (called Host board)
* Seconds HydraUSB3 board shall have PB24 populated with a 2.54mm Jumper (called Device board)

### How to build the firmware source code for HydraUSB3 (CH569W MCU)
It is recommended to use MounRiver Studio "Embedded RISC-V IDE" or "RISC-V IDE (Community)" to build the source code 
* See http://www.mounriver.com/download
* Windows 10 x64 + MounRiver Studio V181 tested with success
* Windows 10 x64 + MounRiver Studio Community Win V120 tested with success
* Ubuntu 20.04 LTS x64 + MounRiver Studio Community Linux V120 tested with success

#### Import examples project(s) in MounRiver Studio (it is based on Eclipse IDE)
* Launch MounRiver Studio (any version MounRiver Studio V181 or MounRiver Studio Community V120 the interface is the same)
  * Select a directory workspace (use the default one)
  * Select Menu `File` => `Import...`
    * In Import Windows choose `General` => `Existing Projects into Workspace`
      * Select `Next >`
      * A window `Import Projects` appears
        * Click on  `Browse` near "Select root directory:" and choose hydrausb3_fw directory
          * Click on `Select Folder`
        * Select the different project(s) you want to import (in `Projects`)
        * Click on `Finish`
  * Project Explorer now show all imported projects
    * Left Click on any project (or choose multiple projects too) to highlight them
    * Right click on the highlighted project and choose `Build Project` or `Build Projects`
    * If all is ok the project shall build fine and display in `Console` "Build Finished. 0 errors, 0 warnings."

### Flashing firmware for HydraUSB3 (CH569W MCU) with ISP Tool(over USB)
### Windows
* Windows 10 x64 + MounRiver Studio V181 execute menu Tools => WCH In-System Programmer
  * See also https://github.com/hydrausb3/wch-isp
* Windows 10 x64 + MounRiver Studio Community Win V120 does not include WCHISPTool / wch-isp so it shall be downloaded and installed
  * See https://github.com/hydrausb3/wch-isp
     * It is the recommended to use the open source multiplatform(GNU/Linux&Windows) command line tool wch-isp to flash the HydraUSB3 CH569W chipset
  	 * Example usage: wch-isp.exe -vr flash fullpath/file.bin
  * See alternative application https://www.wch.cn/downloads/WCHISPTool_Setup_exe.html

### GNU/Linux
* Ubuntu 20.04 LTS x64 + MounRiver Studio Community Linux V120 does not include WCHISPTool / wch-isp so it shall be downloaded/built and installed
  * See https://github.com/hydrausb3/wch-isp
     * It is the recommended to use the open source multiplatform(GNU/Linux&Windows) command line tool wch-isp to flash the HydraUSB3 CH569W chipset
  	 * Example usage: wch-isp -vr flash fullpath/file.bin
