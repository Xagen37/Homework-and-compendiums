package markup;

import java.util.List;

public class Strong extends Paragraph {
    public Strong(List<MarkdownUnit> source) {
        super(source);
    }

    @Override
    public void toMarkdown(StringBuilder source) {
        source.append("__");
        super.toMarkdown(source);
        source.append("__");
    }

    @Override
    public void toHtml(StringBuilder source) {
        source.append("<strong>");
        super.toHtml(source);
        source.append("</strong>");
    }
}
