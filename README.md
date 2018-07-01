# Sampling-PCM-Wave-File
Up/Down Sampling of PCM Wave file

## Instructions to execute the program

    * Download the code into your local maching.
    * Install any C compiler/editor like visual studio/eclipse etc.
    * main.c is the driver file to execute the program.
    * Before executing main.c, edit the PATH and DEST variable pointing to your machine folders
    * PATH contains link to input .wav file and DEST contains destination file where sample file will be writter to.
    * Run main.c
    * It displays the current sampling rate in Hz(Hertz).
    * It prompts the user to enter new frequency in Hz.
    * Enter frequency greater than current frequency to do up sampling and vice versa.
    * Refer the document WavFormatDocs.pdf to read more about .wave file format.
    * Sampling algorithm is based on Sinc Interpolation.
