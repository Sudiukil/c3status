all: README.html

README.html: ../README.md
	pandoc -f markdown_github -t html5 ../README.md -o README.html

clean:
	rm -f README.html
