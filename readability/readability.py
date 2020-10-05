def main():
    plain_text = input("Text: ")
    word_text = len(plain_text.split())
    sent_text = plain_text.count(".") + plain_text.count("!") + plain_text.count("?")
    sum_l = 0
    for l in plain_text:
        sum_l = sum_l + l.isalpha()
    G = round(coleman(sum_l, sent_text, word_text))
    print ("Before Grade 1" if G < 1 else "Grade 16+" if G >= 16 else f"Grade {G}")

def coleman(let, sent, wrd):
    L = (100*let) / wrd
    S = (100*sent) / wrd
    return (0.0588*L - 0.296*S - 15.8)

if __name__ == "__main__":
    main()