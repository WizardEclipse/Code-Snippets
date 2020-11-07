import numpy as np
import matplotlib.pyplot as plt
import os


def caes_break(file):
    a = 'abcdefghijklmnopqrstuvwxyz'

    def frq_from_str(text, sort=False):
        text = text.lower()
        tup_list = []
        for i in list(a):
            tup_list.append((i, 0))
        alph_frq = dict(tup_list)
        # Made dictionary alph_count with keys 'a' to 'z' and values 0 for all.

        for i in list(a):
            alph_frq[i] = (text.count(i) / len(text)) * 100
            # key 'a' through 'z' get the percentage frequencies of themselves in the string
        if sort == False:
            return alph_frq
        if sort == True:
            return {k: v for k, v in sorted(alph_frq.items(), key=lambda item: item[1])}



    def ceas_str(stro, ke):
        a = 'abcdefghijklmnopqrstuvwxyz'
        tem_a = list(a)
        tem_b = np.array(tem_a)
        tem_c = np.roll(tem_b, ke)
        rolly = list(tem_c)
        fin = []

        for i in stro:
            if i.isalpha() == False:
                fin.append(i)
                continue
            va = a.find(i)
            fin.append(rolly[va])
        return "".join(fin)

    eng = [8.12, 1.49, 2.71, 4.32, 12.02, 2.30, 2.03, 5.92, 7.31, 0.10, 0.69, 3.98, 2.61,
           6.95, 7.68, 1.82, 0.11, 6.02, 6.28, 9.10, 2.88, 1.11, 2.09, 0.17, 2.11, 0.07]

    english_frq = dict(zip(list(a), eng))
    # print (english_frq)

    d = open(file, 'r')
    paragraph = d.readlines()

    cipher_frq = frq_from_str(paragraph[0])
    # print(f)
    d.close()

    ###DECRYPTION
    e_cypher = max(cipher_frq, key=cipher_frq.get)
    # print(e_cypher)
    shift = a.find('e') - a.find(e_cypher)

    decrypt_str = ceas_str(paragraph[0], abs(shift))

    ### T and A fitting

    decrypt_str_plus = ceas_str(paragraph[0], abs(shift + 1))
    decrypt_str_minus = ceas_str(paragraph[0], abs(shift - 1))

    a1 = frq_from_str(decrypt_str)
    a_plus = frq_from_str(decrypt_str_plus)
    a_minus = frq_from_str(decrypt_str_minus)

    ##PLOTTING
    plt.figure(figsize=(13, 6))

    # plt.subplot(3,1,1)
    plt.bar(*zip(*cipher_frq.items()), label='Ciphertext')
    plt.bar(*zip(*english_frq.items()), label='English Language', alpha=0.4)
    plt.title('Percentage Frequency per letter')
    plt.legend()
    plt.savefig('break/initial.png')
    plt.show()

    plt.figure(figsize=(13, 3))

    plt.subplot(1, 3, 1)
    # plt.figure(figsize=(13,6))
    plt.bar(*zip(*a_minus.items()), label=f'Key = {abs(shift - 1)}')
    plt.bar(*zip(*english_frq.items()), label='English Language', alpha=0.4)
    plt.suptitle('Percentage Frequency per letter SHIFTED')
    plt.legend()

    plt.subplot(1, 3, 2)
    plt.bar(*zip(*a1.items()), label=f'Key = {abs(shift)}')
    plt.bar(*zip(*english_frq.items()), label='English Language', alpha=0.4)
    # plt.suptitle('Percentage Frequency per letter')
    plt.legend()

    plt.subplot(1, 3, 3)
    # plt.figure(figsize=(12,6))
    plt.bar(*zip(*a_plus.items()), label=f'Key = {abs(shift + 1)}')
    plt.bar(*zip(*english_frq.items()), label='English Language', alpha=0.4)
    # plt.suptitle('Percentage Frequency per letter')
    plt.legend()

    plt.tight_layout()
    plt.savefig('break/compare.png')
    plt.show()

    ## SHOWING
    print(f"Key: {abs(shift)}")
    print()
    print('HIDDEN MESSAGE:')
    print(decrypt_str)

    return {"ciphertext": paragraph[0], "key": abs(shift), "plaintext": decrypt_str}
    
if __name__ == '__main__':
    entries = os.listdir('break/')
    for i in entries:
        if i != 'broken.txt' and i != 'initial.png' and i != 'compare.png' and i[-4:-1] == '.tx':
            di = caes_break(f"break/{i}")
            ret = open('break/broken.txt', 'w')
            L = [f"Key to Break: {di['key']} \n\n\n", f"Decrypted Text: \n{di['plaintext']}"]
            ret.writelines(L)
            ret.close()