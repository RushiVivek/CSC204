# !/bin/bash
echo -n "Enter a character: "
read -n1 C
echo

case $C in
    "A"|"E"|"I"|"O"|"U"|"a"|"e"|"i"|"o"|"u")
    echo "Character is a vowel."
    ;;
    *)
    echo "Character is not a vowel."
    ;;
esac
