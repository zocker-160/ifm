;;; ifm-mode.el --- IFM editing commands for Emacs.
;;; Written by Glenn Hutchings (zondo@hunting2.demon.co.uk)

(defvar ifm-mode-map nil
  "Keymap used in IFM mode.")

(defvar ifm-mode-syntax-table nil
  "Syntax table used in IFM mode.")

(defvar ifm-mode-hook '())

(if ifm-mode-map
    nil
  (setq ifm-mode-map (make-sparse-keymap))
  (define-key ifm-mode-map "\t" 'indent-relative))

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
    (setq ifm-mode-syntax-table (copy-syntax-table))
    (modify-syntax-entry ?_ "w" ifm-mode-syntax-table)
    (set-syntax-table ifm-mode-syntax-table))
  ;; Activate keymap.
  (use-local-map ifm-mode-map)
  (run-hooks 'ifm-mode-hook))
