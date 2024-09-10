$outputDir = (Join-Path $PWD Docs\html)
if (Test-Path -Path $outputDir) {
    Remove-Item -Force -Recurse $outputDir
}

doxygen doxyfile

"
Documentation generated successfully.
"