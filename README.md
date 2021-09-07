# QT_console_application<br><hr>
Console application that accepts a configuration file as a parameter.<br><hr>
<b>Description<br></b><br>
Required functionality<br>
<b>1)</b>The files from which the application should read the parameters must be in .toml format<br> (Filename extension - .toml).<br> Other formats are not supported.;)<br>
<b>2)</b>The main process(thread) must contain threads parallel reading files<br>
, files list must be passed in parameters (arguments command).<br> The application must be multithreaded.<br>
<b>3)</b>All flows shall be approximately equally loaded.<br>
<b>4)</b>Based on the data read from the files, perform data processing.<br>
<b>5)</b>The main thread sums the data and outputs the results.<br>

<b>Settings for the project</b><br>
Visual Studio 2019<br>
Qt 6.1.2<br>
C++ 17<br>
toml<br>
