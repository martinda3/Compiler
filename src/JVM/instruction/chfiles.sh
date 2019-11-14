for f in *.java; do 
    mv -- "$f" "${f%.java}.cpp"
done
