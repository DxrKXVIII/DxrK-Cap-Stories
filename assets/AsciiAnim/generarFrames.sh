for frame in frames/*.png; do
    nombre=$(basename "$frame" .png)
    ./imgAAscii "$frame" > "AsciiFrames/$nombre.txt"
done
