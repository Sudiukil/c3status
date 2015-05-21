all: README.html

README.html: ../README.md
	pandoc -f markdown_github -t html5 ../README.md | sed -e 's/<li><p>/<li>/g' -e 's/<\/p><\/li>/<\/li>/g' > README.html

clean:
	rm -f README.html
