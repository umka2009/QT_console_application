# QT_console_application<br><hr>
Console application that accepts a configuration file as a parameter.<br><hr>
<b>Description<br></b><br>
Required functionality<br>
<b>1)</b>The files from which the application should read the parameters must be in .toml format<br> (Filename extension - .toml).<br> Other formats are not supported.;)<br>
<b>2)</b>The main process(thread) must contain threads parallel reading files.<br> The application must be multithreaded.<br>
<b>3)</b>All flows shall be approximately equally loaded.<br>
<b>4)</b>Based on the data read from the files, perform data processing.<br>
<b>5)</b>In a separate thread summs the data and transfer it to the main stream.<br>
<b>6)</b>The main thread only outputs the results.<br><hr>

<b>Settings for the project</b><br>
Visual Studio 2019<br>
Qt 6.1.2<br>
C++ 17<br>
toml<br>
