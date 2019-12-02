package markup;

public interface MarkdownUnit {
    void toMarkdown(StringBuilder source);
    void toHtml(StringBuilder source);
}
