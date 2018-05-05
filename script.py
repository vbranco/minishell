# **************************************************************************** #
#                                                           LE - /             #
#                                                               /              #
#    script.py                                        .::    .:/ .      .::    #
#                                                  +:+:+   +:    +:  +:+:+     #
#    By: vbranco <marvin@le-101.fr>                 +:+   +:    +:    +:+      #
#                                                  #+#   #+    #+    #+#       #
#    Created: 2018/03/15 14:15:22 by vbranco      #+#   ##    ##    #+#        #
#    Updated: 2018/03/15 20:25:31 by vbranco     ###    #+. /#+    ###.fr      #
#                                                          /                   #
#                                                         /                    #
# **************************************************************************** #

import os
import shutil
import sys
import getopt

class   colors:
    BLUE = '\033[34m'
    RED = '\033[31m'
    GREEN = '\033[32m'
    END = '\033[0m'

def create_makefile(name, header, libft):
    file = open("Makefile", 'w')
    file.write("NAME\t\t" + "=\t" + name + "\n\nHEADER\t\t=\t" + header + "\n\nFILENAMES\t=\tmain.c\n\nSOURCES\t\t=\t$(addprefix ./, $(FILENAMES))\n\nOBJECTS\t\t=\t$(addprefix build/, $(FILENAMES:.c=.o))\n\n")
    if libft == "o":
        file.write("L_FT\t\t=\t./libft\n\nLIB\t\t\t=\t./libft/libft.a\n\nLIB_LNK\t\t=\t-L $(L_FT) - l ft\n\nLIB_INC\t\t=\t-I $(L_FT)/libft.h\n\n")
    file.write("FLAGS\t\t=\t-Wall -Wextra -Werror\n\n.PHONY: all clean fclean re\n\nall: $(NAME)\n\nclean:\n\t\trm -rf build/\n")
    if libft == "o":
        file.write("\t\t@$(MAKE) -C $(L_FT) clean\n\n")
    else:
        file.write("\n")
    file.write("fclean: clean\n\t\t@echo \"\\033[31m\"\n\t\trm -f $(NAME)\n")
    if libft == "o":
        file.write("\t\t@$(MAKE) -C $(L_FT) fclean\n\n")
    else:
        file.write("\n")
    if libft == "o":
        file.write("re:\n\t\t@$(MAKE) fclean\n\t\t@$(MAKE) all\n\n")
    else:
        file.write("re: fclean all\n\n")
    file.write("build:\n\t\t@echo \"\\033[35m\"\n\t\tmkdir build/\n\n$(NAME): $(OBJECTS)\n\t\t")
    if libft == "o":
        file.write("@$(MAKE) -C $(L_FT)\n\t\t")
    file.write("@echo \"\\033[32m\"\n\t\tgcc $(FLAGS) -I $(HEADER) $(SOURCES) $(LIB) -o $@\n\nbuild/%.o: ./%.c | build\n\t\tgcc $(FLAGS) $(LIB_INC) -I $(HEADER) -c $< -o $@")
    file.close()
    os.system("vim Makefile -c ':Stdheader' -c ':x'")

def create_auteur():
    file = open("auteur", 'w')
    file.write(os.environ['LOGNAME'] + '\n')
    file.close()

def create_header(name, header):
    file = open(header, 'w')
    file.write("#ifndef " + name.upper() + "_H" + '\n' + "# define " + name.upper() + "_H\n\n")

    file.write("# include \"libft/libft.h\"\n\n")
    file.close()
    os.system("vim " + name + ".h" + " -c ':Stdheader' -c ':x'")

def create_git():
    file = open(".gitignore", 'w')
    file.write("script.py\n" + "*.swp\n" + "*.out\n" + "*.o\n")
    file.close()

def try_path_lib():
    path = input("Veuillez le saisir a nouveau : ")
    while True:
        if os.path.exists(path):
            shutil.copytree(path, "src/libft")
            break
        else:
            path = input("Etes-vous sur de vouloir inclure la Libft ? (\"o\\n\")\n")
            if path.lower() == "n":
                print (colors.RED + "La Libft n'a pas pu etre copie !" + colors.END)
                break
            else:
                path = input("Veuillez le saisir a nouveau : ")

def import_libft():
    path = input("Veuillez m'indiquer le path de votre Libft : ")
    try:
        os.path.exists(path)
        shutil.copytree(path, "src/libft")
        print (colors.GREEN + "La Libft a ete copie!" + colors.END)
    except:
        print (colors.RED + "Le PATH saisi n'est pas bon !" + colors.END)
        try_path_lib()

def include_libft():
    libft = input("Voulez-vous inclure la LIBFT? (o\\n)\n")
    if libft != "O" and libft != "o" and libft != "N" and libft != "n":
        while  True:
            libft = input("Veuillez repondre \"o\" ou \"n\"\n")
            if libft == "O" or libft == "o" or libft == "N" or libft == "n":
                break
    if libft.lower() == "o":
        import_libft()
    else:
        try:
            os.mkdir('src')
            os.mkdir('src/lib')
            print (colors.GREEN + "Le dossier \"src/lib\" a ete cree !" + colors.END)
        except:
            print (colors.RED + "Le dossier \"src/lib\" n'a pas pu etre cree !" + colors.END)
    return libft.lower()


def main(argv):
    hel = "-h"
    if len(sys.argv) > 1:
        if sys.argv[1] != hel:
            print ("usage : python3 script.py -h for help")
        else:
            print ("Ce script a besoin d'un NOM DE PROJET et d'un LANGAGE de programmation valide pour fonctionner correctement !\nSi vous choisissez le langage C, un Makefile et un fichier header seront crees. \nUn gitignore est cree peut importe le langage choisi.")
    else:
        name = input("----- BONJOUR -----\nQuel est le nom de votre projet?\n")
        header = name + ".h"
        create_auteur()
        print (colors.GREEN + "Le fichier auteur a ete cree !" + colors.END)
        langage = input("Quel langage?\n")
        if langage == "C" or langage == "c":
            libft = include_libft()
            create_makefile(name, header, libft)
            print (colors.GREEN + "Le Makefile a ete cree !" + colors.END)
            create_header(name, header)
            print (colors.GREEN + "Le fichier header a ete cree !" + colors.END)
            create_git()
            print (colors.GREEN + "Le fichier .gitignore a ete cree !" + colors.END)
        else:
            create_git()
            print (colors.GREEN + "Le fichier .gitignore a ete cree !" + colors.END)

if __name__== "__main__":
    main(sys.argv[1:])
