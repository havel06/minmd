# minmd
> a minimal Markdown viewer

## What it does

The application is mainly meant for powerusers and UNIX philosophy
enthusiasts, who are looking for a straight-forward way to read 
a nicely displayed Markdown file, without using any bloated editors
or messing with pandoc.

- Takes in text in Markdown syntax, and displays with formatting
specified by a stylesheet.
- Has vim-like keyboard shortcuts (see below).

## Installation

TODO

## Usage

The application can either read from standard input, or from a file.

```sh
cat file.md | minmd
```

```sh
minmd file.md
```

### Keyboard shortcuts

- `q` - quit
- `j` - scroll down
- `k` - scroll up
- `gg` - go to top of document
- `gg` - go to bottom of document
- `ctrl+j` - long scroll down
- `ctrl+k` - long scroll up

### Configuration

These are the parameters you can change inside `minmd.conf`:

- `widget_spacing` - space between widgets/paragraphs (default: `20`)
- `window_width` - prefered window width (default: `800`)
- `window_height` - prefered window height (default: `600`)
- `indent_size` - left margin of widgets such as lists or quotes (default: `20`)
- `vim_scroll_distance` - vim bindings scrolling distance (default: `30`) 
- `vim_long_scroll_distance`- vim bindings long scrolling distance (default: `300`) 
- `text_selectable` - whether the text is selectable (default: `0`);

## Future goals

- Custom styling of inline code (possible after switching Gtk::Label to Gtk::TextView)
- Tasks
- Tables
