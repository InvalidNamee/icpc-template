MAIN := main.tex
OUTPUT_DIR := output/pdf
JOBNAME := icpc-template
PDF := $(OUTPUT_DIR)/$(JOBNAME).pdf

.PHONY: all pdf clean watch

all: pdf

pdf:
	@mkdir -p $(OUTPUT_DIR)
	latexmk -xelatex -shell-escape -file-line-error -halt-on-error \
		-interaction=nonstopmode -jobname=$(JOBNAME) \
		-outdir=$(OUTPUT_DIR) $(MAIN)

watch:
	@mkdir -p $(OUTPUT_DIR)
	latexmk -pvc -xelatex -shell-escape -file-line-error \
		-interaction=nonstopmode -jobname=$(JOBNAME) \
		-outdir=$(OUTPUT_DIR) $(MAIN)

clean:
	latexmk -C -jobname=$(JOBNAME) -outdir=$(OUTPUT_DIR) $(MAIN)

