;;; ifm-mode.el --- IFM editing commands for Emacs.
;;; Written by Glenn Hutchings (zondo@pillock.freeserve.co.uk)

(defvar ifm-mode-map nil
  "Keymap used in IFM mode.")

(defvar ifm-mode-syntax-table nil
  "Syntax table used in IFM mode.")

(defvar ifm-mode-hook '())

(if ifm-mode-map
    nil
  (setq ifm-mode-map (make-sparse-keymap))
  (define-key ifm-mode-map "\t" 'indent-relative))

(defconst ifm-structure-regexp
  (regexp-opt '("room") 'words)
  "Regexp matching structure keywords in IFM mode.")

(defconst ifm-direction-regexp
  (regexp-opt '("n" "north" "ne" "northeast" "e" "east" "se" "southeast"
		"s" "south" "sw" "southwest" "w" "west" "nw" "northwest")
	      'words)
  "Regexp matching direction names in IFM mode.")

(defconst ifm-special-regexp
  (regexp-opt '("endstyle" "style" "title" "map" "start" "finish" "safe"
		"require") 'words)
  "Regexp matching special keywords in IFM mode.")

(defconst ifm-builtin-regexp
  (regexp-opt '("all" "any" "it" "last" "none" "undef") 'words)
  "Regexp matching builtin names in IFM mode.")

(defconst ifm-keyword-regexp
  (regexp-opt '("after" "before" "cmd" "d" "do" "down" "dir" "drop" "except"
		"exit" "follow" "from" "get" "give" "go" "goto" "hidden"
		"ignore" "in" "item" "join" "keep" "leave" "length" "link"
		"lose" "lost" "need" "nodrop" "nolink" "nopath" "note"
		"oneway" "out" "score" "tag" "task" "to" "u" "up" "until"
		"with") 'words)
  "Regexp matching general keywords in IFM mode.")

(defconst ifm-preprocessor-regexp
  (regexp-opt '("%include" "%define" "%defeval" "%if" "%ifdef" "%undef"
		"%ifndef" "%ifeq" "%ifneq" "%else" "%endif" "%eval"
		"%1" "%2" "%3" "%4" "%5" "%6" "%7" "%8" "%9"
		"%exec" "defined") 'words)
  "Regexp matching preprocessor directives in IFM mode.")

(defconst ifm-obsolete-regexp
  (regexp-opt '("given" "times") 'words)
  "Regexp matching obsolete keywords in IFM mode.")

(defconst ifm-font-lock-keywords
  (list
   (cons "#.*" font-lock-comment-face)
   (cons "\"[^\"]*\"" font-lock-string-face)
   (cons ifm-special-regexp font-lock-constant-face)
   (cons ifm-structure-regexp font-lock-function-name-face)
   (cons ifm-direction-regexp font-lock-variable-name-face)
   (cons ifm-keyword-regexp font-lock-keyword-face)
   (cons ifm-builtin-regexp font-lock-builtin-face)
   (cons ifm-preprocessor-regexp font-lock-builtin-face)
   (cons ifm-obsolete-regexp font-lock-warning-face)
   )
  "Font-lock keywords in IFM mode.")

(add-hook 'ifm-mode-hook
	  (function (lambda ()
		      (make-local-variable 'font-lock-defaults)
		      (setq font-lock-defaults '(ifm-font-lock-keywords t)))))

(defun ifm-mode ()
  "Major mode for editing Interactive Fiction maps.

This mode doesn't really do anything yet -- it's just a mode so that
syntax highlighting can work on it.

Calling this function invokes the function(s) \"ifm-mode-hook\"
before doing anything else."
  (interactive)
  (kill-all-local-variables)
  (setq comment-start "# ")
  (setq comment-end "")
  (setq comment-column 0)
  (setq comment-start-skip "#[ \t]*")
  ;; Become the current major mode.
  (setq major-mode 'ifm-mode)
  (setq mode-name "IFM")
  ;; Activate syntax table.
  (if ifm-mode-syntax-table
      nil
    (setq ifm-mode-syntax-table (make-syntax-table))
    (modify-syntax-entry ?_ "w" ifm-mode-syntax-table))
  (set-syntax-table ifm-mode-syntax-table)
  ;; Activate keymap.
  (use-local-map ifm-mode-map)
  (run-hooks 'ifm-mode-hook))
